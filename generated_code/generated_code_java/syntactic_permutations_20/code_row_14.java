import java.util.*;
class Offset { 
    public static void main(String[] args) {
        int offset = Integer.parseInt(args[0]); //reads in the value from the command line
        System.out.println("Value read from command line is: " + offset);
        
        final int CONSTANT_OFFSET= 5; //constant value that is added to the value read in from the command line
        System.out.println("Constant offset is: " + CONSTANT_OFFSET);
        
        int result = offset + CONSTANT_OFFSET;//adds an offset is a constant value to the value read in from the command line
        System.out.println("The result of adding the offset and the constant offset is: " + result);
    }
}