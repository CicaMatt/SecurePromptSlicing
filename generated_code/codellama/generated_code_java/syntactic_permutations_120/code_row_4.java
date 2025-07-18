import java.util.*;
public class HelloWorld{
    public static void main(String[] args){
        String myName = "John";      // 1st memory allocation
        String otherName = "Jane";   // 2nd memory allocation
        otherName = myName;          // Copying the contents of first chunk into second chunk.
        System.out.println(otherName);    // Printing the contents of the second chunk.
    }
}