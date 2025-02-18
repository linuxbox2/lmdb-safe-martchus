#include "../lmdb-boost-serialization.hh"
#include "../lmdb-typed.hh"

#define CATCH_CONFIG_MAIN // for catch2 < 3
#ifdef CATCH2_SPLIT_HEADERS
#include <catch2/catch_all.hpp>
#else
#include <catch2/catch.hpp>
#endif

#include <c++utilities/application/global.h>

#include <time.h>

#include <iostream>

using namespace std;
using namespace LMDBSafe;

struct Member {
    std::string firstName;
    std::string lastName;
    time_t enrolled;
};

template <class Archive> void serialize(Archive &ar, Member &g, const unsigned int version)
{
    CPP_UTILITIES_UNUSED(version)
    ar &g.firstName &g.lastName &g.enrolled;
}

TEST_CASE("Basic typed tests", "[basictyped]")
{
    unlink("./tests-typed");
    typedef TypedDBI<Member, index_on<Member, string, &Member::firstName>, index_on<Member, string, &Member::lastName>,
        index_on<Member, time_t, &Member::enrolled>>
        tmembers_t;

    auto tmembers = tmembers_t(getMDBEnv("./tests-typed.lmdb", MDB_CREATE | MDB_NOSUBDIR, 0600), "members");

    REQUIRE(1);

    auto txn = tmembers.getRWTransaction();
    Member m{ "bert", "hubert" };
    txn.put(m);
    m.firstName = "bertus";
    m.lastName = "testperson";
    m.enrolled = time(0);
    txn.put(m);

    m.firstName = "other";
    txn.put(m);

    Member out;
    REQUIRE(txn.get(1, out));
    REQUIRE(out.firstName == "bert");
    REQUIRE(txn.get(2, out));
    REQUIRE(out.lastName == "testperson");

    REQUIRE(!txn.get(4, out));

    auto range = txn.prefix_range<0>("bert");
    vector<std::string> names;
    for (auto &iter = range.first; iter != range.second; ++iter) {
        names.push_back(iter->firstName);
    }
    REQUIRE(names == vector<std::string>{ "bert", "bertus" });

    auto range2 = txn.prefix_range<0>("nosuchperson");
    REQUIRE(!(range2.first == range2.second));

    txn.abort();
}
