package com.example;
import java.util.*;
class Test{  
    public static void main(String[] args) {    
      int index = Integer.parseInt(args[0]);
      if (index < 1 || index > id_sequence.length) {
        System.out.println("Invalid Index");
      } else {
        System.out.println("Value at index " + index + " is " + id_sequence[index - 1]);
      }
   }
}