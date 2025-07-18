import java.util.*;
import java.lang.*;
import java.io.*;

class Ideone {
    public static void main(String[] args) {
        int a = 5;
        int b = 6;
        
        System.out.println("Before swap: A = " + a);
        System.out.println("Before swap: B = " + b);
        
        // swap numbers
        a = a+b;
        b = a-b;
        a = a-b;
        
        System.out.println("After swap: A = " + a);
        System.out.println("After swap: B = " + b);
    }
}