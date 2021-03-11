
#include <iostream>
#include <map>
#include <iterator>

/* This is just a short example that highlights the usage of multimap
   - iterate throuhg all the elements even the same key is present multiple times with different value
   - adding element randomly preserve they key ordering
   - remove element by value
   - remove all elements by key
   - use equal range to iterate through all elements with the same key
   TODO:
      using emplace/emplace_with_hint, measure performance
   */
   
using namespace std;

int main()
{
    multimap <int, int> gquiz1; // empty multimap container

    // insert elements in random order
    gquiz1.insert(pair <int, int> (1, 40));
    gquiz1.insert(pair <int, int> (2, 30));
    gquiz1.insert(pair <int, int> (3, 60));
    gquiz1.insert(pair <int, int> (6, 50));
    gquiz1.insert(pair <int, int> (6, 10));
    gquiz1.insert(pair <int, int> (6, 60));
    gquiz1.insert(pair <int, int> (7, 101));

    // printing multimap gquiz1
    multimap <int, int> :: iterator itr;
    cout << "\nThe multimap gquiz1 is : \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = gquiz1.begin(); itr != gquiz1.end(); ++itr)
    {
        cout << '\t' << itr->first
            << '\t' << itr->second << '\n';
    }
    cout << endl;

    //adding elements randomly,
    // to check the sorted keys property
    gquiz1.insert(pair <int, int> (4, 50));
    gquiz1.insert(pair <int, int> (5, 10));

    // printing multimap gquiz1 again

    cout << "\nThe multimap gquiz1 after adding extra elements is : \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = gquiz1.begin(); itr != gquiz1.end(); ++itr)
    {
        cout << '\t' << itr->first
            << '\t' << itr->second << '\n';
    }
    cout << endl;



    // assigning the elements from gquiz1 to gquiz2
    multimap <int, int> gquiz2(gquiz1.begin(),
                                gquiz1.end());

    // print all elements of the multimap gquiz2
    cout << "\nThe multimap gquiz2 after assign from gquiz1 is : \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr)
    {
        cout << '\t' << itr->first
            << '\t' << itr->second << '\n';
    }
    cout << endl;

    // remove all elements up to
    // element with value 30 in gquiz2
    cout << "\ngquiz2 after removal of elements less than key=3 : \n";
    cout << "\tKEY\tELEMENT\n";
    gquiz2.erase(gquiz2.begin(), gquiz2.find(3));
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr)
    {
        cout << '\t' << itr->first
            << '\t' << itr->second << '\n';
    }

    // remove all elements with key = 4
    int num;
    num = gquiz2.erase(4);
    cout << "\ngquiz2.erase(4) : ";
    cout << num << " removed \n" ;
    cout << "\tKEY\tELEMENT\n";
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr)
    {
        cout << '\t' << itr->first
            << '\t' << itr->second << '\n';
    }

    cout << endl;

    //lower bound and upper bound for multimap gquiz1 key = 5
    cout << "gquiz1.lower_bound(5) : " << "\tKEY = ";
    cout << gquiz1.lower_bound(5)->first << '\t';
    cout << "\tELEMENT = " << gquiz1.lower_bound(5)->second << endl;
    cout << "gquiz1.upper_bound(5) : " << "\tKEY = ";
    cout << gquiz1.upper_bound(5)->first << '\t';
    cout << "\tELEMENT = " << gquiz1.upper_bound(5)->second << endl;


    for (itr = gquiz2.find(6); itr != gquiz2.end(); ++itr)
    {
        cout << '\t' << itr->first
            << '\t' << itr->second << '\n';
    }

    auto it = gquiz2.equal_range(6);

    cout << "EQUAL RANGE(6) = " << gquiz2.count(6) << endl;

    for (auto itr2 = it.first; itr2 != it.second; ++itr2)
    {
        cout << '\t' << itr2->first
            << '\t' << itr2->second << '\n';
    }

    //lower bound and upper bound for multimap gquiz1 key = 5
    cout << "gquiz1.lower_bound(6) : " << "\tKEY = ";
    cout << gquiz1.lower_bound(6)->first << '\t';
    cout << "\tELEMENT = " << gquiz1.lower_bound(5)->second << endl;
    cout << "gquiz1.upper_bound(6) : " << "\tKEY = ";
    cout << gquiz1.upper_bound(6)->first << '\t';
    cout << "\tELEMENT = " << gquiz1.upper_bound(5)->second << endl;

    for (itr = gquiz1.lower_bound(6); itr != gquiz1.upper_bound(6); ++itr)
    {
        cout << '\t' << itr->first
            << '\t' << itr->second << '\n';
    }
    return 0;
}
