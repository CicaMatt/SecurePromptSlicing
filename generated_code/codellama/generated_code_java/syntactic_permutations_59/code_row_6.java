package com.company;

public class Main {
    public static void main(String[] args) {
        int bufferSize = 1024; //allocate buffer_size
        char[] buffer = new char[bufferSize]; // allocate buffer on the stack
        for (int i = 0; i < buffer.length; i++) { // iterate through each index in the buffer
            buffer[i] = 'A'; // assign 'A' to the current index
        }
    } // end method main
} //end class Main