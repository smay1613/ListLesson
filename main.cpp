#include <iostream>
#include <list>

struct SomeClass
{
    SomeClass() {
        std::cout << "Some class default constructed!" << std::endl;
    }
    SomeClass(size_t data) {
        std::cout << "Some class constructed with param " << std::to_string(data) << std::endl;
    }
    SomeClass(const SomeClass&) {
        std::cout << "Some class copy constructed" << std::endl;
    }
    SomeClass(SomeClass&&) {
        std::cout << "Some class move constructed" << std::endl;
    }
    ~SomeClass() {
        std::cout << "Some class destroyed" << std::endl;
    }
};

template<class T>
void printList(const std::list<T>& listToPrint)
{
    static const T defaultEntry {};
    for (const auto& entry : listToPrint) { // range for
        if (entry == defaultEntry) {
            std::cout << "<default entry>" << std::endl;
        } else {
            std::cout << entry << std::endl;
        }
    }
    std::cout << std::endl;
}

void investigateCapacityOperations(const std::list<std::string>& data)
{
    // Capacity operations
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "File list size: " << data.size() << std::endl;
    std::cout << "File list max size: " << data.max_size() << std::endl;

    if (data.empty()) { // check for size == 0
        std::cout << "File list is empty!" << std::endl;
    } else {
        std::cout << "File list is not empty. " << std::endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void investigateAccessOperations(const std::list<std::string>& data)
{
    // Element access
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::cout << "First element: " << data.front() << std::endl; // read only access to the first element
    std::cout << "Last element: " << data.back() << std::endl; // read only access to the last element

    auto start = data.begin();
    std::advance(start, 2); // or std::next
    std::cout << *start << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void investigateModifiers(std::list<std::string>& data)
{
    // Modifiers
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    data.clear(); // deletes the data
    std::cout << "List cleared! It's size now is " << data.size() << std::endl;
    const size_t filesCount {3};

    for (size_t i = 0; i < filesCount; ++i) {
        std::string fileName {std::to_string(i) + ".mp3"};
        data.push_back(fileName); // add one element to the end

        std::cout << "Appended [" << i + 1<< "]/[" << filesCount << "] " << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;

    std::list<SomeClass> someData;
    const size_t someSize {3};
    for (size_t i = 0; i < someSize; ++i) {
        someData.emplace_back(i); // in-place adding one element to the end

        std::cout << "Emplaced [" << i + 1 << "]/[" << someSize << "] " << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;

    std::list<SomeClass> someData2;
    for (size_t i = 0; i < someSize; ++i) {
        SomeClass someObject {i};
        someData2.push_back(someObject); // add one element to the end

        std::cout << "Pushed [" << i + 1 << "]/[" << someSize << "] " << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;

    for (size_t i = 0; i < filesCount / 2; ++i) {
        data.pop_back(); // remove one element at the end

        std::cout << "Popped [" << i + 1 << "]/[" << filesCount / 2 << "] " << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Before insertion: " << std::endl;
    printList(data);

    std::cout << "After insertion: " << std::endl;
    const std::string discoveredFile {"newfile.jpg"};
    data.insert(std::next(data.begin(), 2), discoveredFile); // adds an element to a specified position
    printList(data);

    std::cout << "After emplace insertion: " << std::endl;
    data.emplace(std::next(data.begin(), 3), "newfile.png"); // inserts inplace without copy
    printList(data);

    std::list<std::string> newDiscoverage {".gitignore", "hellolist.cpp", "Makefile"};
    std::cout << "New discoverage content: " << std::endl;
    printList(newDiscoverage);

    std::list<std::string> oldDiscoverage {data};
    oldDiscoverage.resize(3); // change size to 3
    std::cout << "Old discoverage content: " << std::endl;
    printList(oldDiscoverage);
    std::cout << "After swapping, oldDiscoverage content: " << std::endl;

    newDiscoverage.swap(oldDiscoverage); // exchanges content
    printList(oldDiscoverage);

    oldDiscoverage.erase(oldDiscoverage.begin()); // removes first element
    std::cout << "After erasing first element old discoverage is: " << std::endl;
    printList(oldDiscoverage);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::cout << "Pushing and emplacing front coverart" << std::endl;
    oldDiscoverage.push_front("coverart.jpg"); // adds element at beginning
    oldDiscoverage.emplace_front("coverart.png");
    printList(oldDiscoverage);

    std::cout << "Pop front coverart" << std::endl;
    oldDiscoverage.pop_front(); // adds element at beginning
    printList(oldDiscoverage);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void investigateOperations()
{
    std::list<std::string> fileList {
        "hello.h",
        "world.png",
        "we.jpg",
        "are.wav",
        "investigating.iso",
        "list.cpp"
    };

    std::cout << "File list 1 content: " << std::endl;
    printList(fileList);

    std::list<std::string> fileList2 {
        "hello.h",
        "hellotest.wmv"
    };

    std::cout << "File list 2 content:  " << std::endl;
    printList(fileList2);

    fileList.sort(); // before merge, must be sorted in asc order!
    fileList2.sort();

    fileList.merge(fileList2); // fileList2 is merged into fileList, fileList2 is empty

    std::cout << "Merged into file list 1, result content: " << std::endl;
    printList(fileList);

    std::cout << "File list 2 content:  " << std::endl;
    printList(fileList2);

    std::cout << "Add some data to fileList2:" << std::endl;
    fileList2.assign(3, "test.cxx");
    printList(fileList2);

    fileList.splice(fileList.begin(), fileList2); // fileList2 is moved to fileList

    std::cout << "Spliced into file list 1, result content: " << std::endl;
    printList(fileList);
    std::cout << "File list 2 content:  " << std::endl;
    printList(fileList2);

    std::cout << "Removing duplicate entries..." << std::endl;
    fileList.unique();
    printList(fileList);

    std::cout << "Reversing entries..." << std::endl;
    fileList.reverse();
    printList(fileList);

    std::cout << "Removing list.cpp entry..." << std::endl;
    fileList.remove("list.cpp");
    printList(fileList);

    fileList.insert(fileList.begin(), 3, "");
    std::cout << "Adding some empty entries, result: " << std::endl;
    printList(fileList);

    std::cout << "Removing empty entries" << std::endl;
    fileList.remove_if( [](const std::string& entry) {
        return entry.empty();
    });
    printList(fileList);
}

int main()
{
    std::list<std::string> fileList {
        "1.mp3",
        "2.mp3",
        "3.mp3",
        "4.mp3",
        "5.mp3"
    };
    investigateCapacityOperations(fileList);
    investigateAccessOperations(fileList);
    investigateModifiers(fileList);
    investigateOperations();
    return 0;
}
