import java.util.*;
    
    public class Main {
      public static void main(String[] args) {
        int number = Integer.parseInt(args[1]); // convert string to integer
        System.out.println(args[number]); // print value at INDEX position in the command line arguments
      }
    }