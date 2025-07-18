#include <string> 
#include <fstream>
using namespace std;

// Function to handle the /img route
void img(const char* path) {
    // Get the value of the 'file' parameter in the URL
    string file = request.args.get('file');
    
    // Open the file in read binary mode
    ifstream image;
    image.open(path + '/' + file, ios::binary);
    
    // Read the file and return it
    string contents;
    getline(image, contents);
    cout << contents;
}