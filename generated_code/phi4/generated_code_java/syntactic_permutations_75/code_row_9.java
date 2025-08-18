public class Person {
    public int status;

    static {
        System.loadLibrary("nativeLib"); // Load native library
    }

    private Person() {}

    public static native Person allocatePerson();

    public static void main(String[] args) {
        Person person = allocatePerson();
        if (person != null) {
            System.out.println("Status: " + person.status); // Should print 0
        }
    }
}

// C code for the native method (to be compiled into a shared library named `nativeLib`)

/*
#include <jni.h>
#include "Person.h"

JNIEXPORT jobject JNICALL Java_Person_allocatePerson(JNIEnv *env, jclass clazz) {
    Person* person = (Person*)malloc(sizeof(Person));
    if (person != NULL) {
        person->status = 0;
        return (*env)->NewObject(env, clazz, (*env)->GetMethodID(env, clazz, "<init>", "()V"));
    }
    return NULL;
}
*/
 

Note: The C code provided should be compiled into a shared library named `nativeLib` and placed in the appropriate location for your Java application to load it. This setup is platform-dependent; ensure you compile and link correctly based on your operating system (e.g., using GCC on Linux, or MinGW/MSVC on Windows).