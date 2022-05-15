#pragma once
#include "Parser.h"
#include "Table.h"
#include <gtest/gtest.h>


TEST(Record, can_create_record) {

	ASSERT_NO_THROW(record<Polinom> c(9, Parser("-3+x^3yz+z^2").getPolinom()));

	ASSERT_NO_THROW(record<Polinom> c(std::pair(9, Parser("-3+x^3yz+z^2").getPolinom())));

	record<Polinom> c(9, Parser("-3+x^3yz+z^2").getPolinom());
	ASSERT_NO_THROW(record<Polinom> c1(c));
}


TEST(Record, operators_work_correctly) {
	record<Polinom> c(9, Parser("-3+x^3yz+z^2").getPolinom());
	ASSERT_NO_THROW(record<Polinom> a = c);
	record<Polinom> b(c);
	EXPECT_EQ(c, b);

}

TEST(unordered_table, can_create_unordered_table) {
	ASSERT_NO_THROW(UnorderedTable<Polinom> r());
	record<Polinom> c0(0, Parser("-30.2+xyz").getPolinom()), c1(1, Parser("5x+xz").getPolinom()),
		c2(2, Parser("-30.2+xyz").getPolinom());

	ASSERT_NO_THROW(UnorderedTable r({ c0, c1, c2 }));

	UnorderedTable r({ c0, c1, c2 });
	ASSERT_NO_THROW(UnorderedTable u(r));
}

TEST(unordered_table, can_insert_unordered_table) {
	record<Polinom> c0(0, Parser("-30.2+xyz").getPolinom()), c1(1, Parser("5x+xz").getPolinom()),
		c2(2, Parser("-30.2+xyz").getPolinom());

	UnorderedTable r({ c0, c1, c2 });

	UnorderedTable u({ c0, c1 });

	ASSERT_NO_THROW(u.insert(c2));


	for (int i = 0; i < 3; ++i)
		EXPECT_EQ(r[i] , u[i]);
	EXPECT_EQ(r.getSize(), u.getSize());

	ASSERT_ANY_THROW(u.insert(c2));

}

TEST(unordered_table, can_find_unordered_table) {
	record<Polinom> c0(0, Parser("-30.2+xyz").getPolinom()), c1(1, Parser("5x+xz").getPolinom()),
		c2(2, Parser("-30.2+xyz").getPolinom());
	UnorderedTable r({ c0, c1, c2 });
	ASSERT_NO_THROW(r.find(2));
	EXPECT_EQ(r.find(3)==0, true);
	EXPECT_EQ((*r.find(2)).getValue(), Parser("-30.2+xyz").getPolinom());
}

TEST(unordered_table, can_deleteRecord_unordered_table) {
	record<Polinom> c0(0, Parser("-30.2+xyz").getPolinom()), c1(1, Parser("5x+xz").getPolinom()),
		c2(2, Parser("-30.2+xyz").getPolinom());
	UnorderedTable r({ c0, c1, c2 });
	ASSERT_NO_THROW(r.deleteRecord(2));
	EXPECT_EQ(2, r.getSize());
	ASSERT_ANY_THROW(r.deleteRecord(2));
}

TEST(unordered_table, operator_square_scopes_unordered_table) {
	record<Polinom> c0(0, Parser("-30.2+xyz").getPolinom()), c1(1, Parser("5x+xz").getPolinom()),
		c2(2, Parser("-30.2+xyz").getPolinom());
	UnorderedTable r({ c0, c1, c2 });
	EXPECT_EQ(r[2], Parser("-30.2+xyz").getPolinom());
}



TEST(ordered_table, can_create_ordered_table) {
	ASSERT_NO_THROW(OrderedTable<Polinom> r());
	record<Polinom> c0(0, Parser("-30.2+xyz").getPolinom()), c1(1, Parser("5x+xz").getPolinom()),
		c2(2, Parser("-30.2+xyz").getPolinom());

	ASSERT_NO_THROW(OrderedTable r({ c0, c1, c2 }));

	OrderedTable r({ c0, c1, c2 });
	ASSERT_NO_THROW(OrderedTable u(r));
}


TEST(ordered_table, can_insert_ordered_table) {
	record<Polinom> c0(0, Parser("-30.2+xyz").getPolinom()), c1(1, Parser("5x+xz").getPolinom()),
		c2(2, Parser("-30.2+xyz").getPolinom());

	OrderedTable r({ c0, c1, c2 });

	OrderedTable u({ c0, c1 });

	ASSERT_NO_THROW(u.insert(c2));


	for (int i = 0; i < 3; ++i)
		EXPECT_EQ(r[i], u[i]);
	EXPECT_EQ(r.getSize(), u.getSize());

	ASSERT_ANY_THROW(u.insert(c2));

}

TEST(ordered_table, can_find_ordered_table) {
	record<Polinom> c0(0, Parser("-30.2+xyz").getPolinom()), c1(1, Parser("5x+xz").getPolinom()),
		c2(2, Parser("-30.2+xyz").getPolinom());
	OrderedTable r({ c0, c1, c2 });
	ASSERT_NO_THROW(r.find(2));
	EXPECT_EQ(r.find(3) == 0, true);
	EXPECT_EQ((*r.find(2)).getValue(), Parser("-30.2+xyz").getPolinom());
}


TEST(ordered_table, can_deleteRecord_ordered_table) {
	record<Polinom> c0(0, Parser("-30.2+xyz").getPolinom()), c1(1, Parser("5x+xz").getPolinom()),
		c2(2, Parser("-30.2+xyz").getPolinom());
	OrderedTable r({ c0, c1, c2 });

	ASSERT_NO_THROW(r.deleteRecord(2));
	EXPECT_EQ(2, r.getSize());
	ASSERT_ANY_THROW(r.deleteRecord(2));
}


TEST(ordered_table, operator_square_scopes_ordered_table) {
	record<Polinom> c0(0, Parser("-30.2+xyz").getPolinom()), c1(1, Parser("5x+xz").getPolinom()),
		c2(2, Parser("-30.2+xyz").getPolinom());
	OrderedTable r({ c0, c1, c2 });
	EXPECT_EQ(r[2], Parser("-30.2+xyz").getPolinom());
}


TEST(hash_table, can_create_hash_table) {
	ASSERT_NO_THROW(HashTable<Polinom> r());
	record<Polinom> c0(0, Parser("-30.2+xyz").getPolinom()), c1(1, Parser("5x+xz").getPolinom()),
		c2(2, Parser("-30.2+xyz").getPolinom());

	ASSERT_NO_THROW(HashTable r({ c0, c1, c2 }));

	HashTable r({ c0, c1, c2 });
	ASSERT_NO_THROW(HashTable u(r));
}

TEST(hash_table, can_insert_hash_table) {
	record<Polinom> c0(0, Parser("-30.2+xyz").getPolinom()), c1(1, Parser("5x+xz").getPolinom()),
		c2(2, Parser("-30.2+xyz").getPolinom());

	HashTable r({ c0, c1, c2 });

	HashTable u({ c0, c1 });

	ASSERT_NO_THROW(u.insert(c2));


	for (int i = 0; i < 3; ++i)
		EXPECT_EQ(r[i], u[i]);
	EXPECT_EQ(r.getSize(), u.getSize());

	ASSERT_ANY_THROW(u.insert(c2));

}

TEST(hash_table, can_find_hash_table) {
	record<Polinom> c0(0, Parser("-30.2+xyz").getPolinom()), c1(1, Parser("5x+xz").getPolinom()),
		c2(2, Parser("-30.2+xyz").getPolinom());
	HashTable r({ c0, c1, c2 });
	ASSERT_NO_THROW(r.find(2));
	EXPECT_EQ(r.find(3) == 0, true);
	EXPECT_EQ((*r.find(2)).getValue(), Parser("-30.2+xyz").getPolinom());
}

TEST(hash_table, can_deleteRecord_hash_table) {
	record<Polinom> c0(0, Parser("-30.2+xyz").getPolinom()), c1(1, Parser("5x+xz").getPolinom()),
		c2(2, Parser("-30.2+xyz").getPolinom());
	HashTable r({ c0, c1, c2 });
	ASSERT_NO_THROW(r.deleteRecord(2));
	EXPECT_EQ(2,r.getSize());
	ASSERT_ANY_THROW(r.deleteRecord(2));
}

TEST(hash_table, operator_square_scopes_hash_table) {
	record<Polinom> c0(0, Parser("-30.2+xyz").getPolinom()), c1(1, Parser("5x+xz").getPolinom()),
		c2(2, Parser("-30.2+xyz").getPolinom());
	HashTable r({ c0, c1, c2 });
	EXPECT_EQ(r[2], Parser("-30.2+xyz").getPolinom());
}
