#include <iostream>
#include <stdexcept>
#include <SWI-cpp2.h>

/** fast interface to get a string out of a ground term.
  * thanks Jan !
  */
std::wstring serialize(PlTerm t) {
    wchar_t* s;

    if (PL_get_wchars(t.unwrap(), NULL, &s, CVT_WRITEQ | BUF_RING))
        return s;

    throw PlTypeError("serialize", t);
}

void test1() {
    using namespace std;

    PlTermv av(2);
    PlTerm_tail l(av[1]);
    for (long i : { 1,2,3 })
        if (!l.append(PlTerm_integer(i)))
            throw runtime_error("!l.append(PlTerm_integer(i))");
    if (!l.close())
        throw runtime_error("!l.close()");

    PlQuery q("member", av);
    while (q.next_solution()) {
        cout << av[0].as_string() << ',' << av[1].as_string() << endl;
        wcout << av[0].as_wstring() << ',' << av[1].as_wstring() << endl;
        wcout << serialize(av[0]) << ',' << serialize(av[1]) << endl;
    }

    extern void test_opencv(string path);
    test_opencv(R"(C:\Users\cccar\Pictures\test\single.png)");
}

int main(int argc, char* argv[])
{
    PlEngine e(argc, argv);
    std::cout << "Hello swipl!\n";
    try {
        test1();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
