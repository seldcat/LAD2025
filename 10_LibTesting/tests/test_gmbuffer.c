#include <check.h>
#include "gmbuffer.h"

typedef struct {
    char *data;
    size_t len;
    size_t cap;
} buf_t;

START_TEST(test_init)
{
    buf_t b;
    GM_INIT(&b);

    ck_assert_ptr_null(b.data);
    ck_assert_uint_eq(b.len, 0);
    ck_assert_uint_eq(b.cap, 0);
}
END_TEST

START_TEST(test_reserve)
{
    buf_t b;
    GM_INIT(&b);

    int rc = gm_reserve((void**)&b.data, &b.cap, 100);
    ck_assert_int_eq(rc, 0);
    ck_assert_uint_ge(b.cap, 100);

    GM_FREE(&b);
}
END_TEST

Suite *gmbuffer_suite(void)
{
    Suite *s = suite_create("gmbuffer");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_init);
    tcase_add_test(tc, test_reserve);

    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    Suite *s = gmbuffer_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);

    srunner_free(sr);
    return failed ? 1 : 0;
}
