import java.io.*;
class Java{
    public static void main(String[] args){
        int n = Integer.parseInt(args[0]); // Get the buffer size from the command line argument 
        byte[] b = new byte[n]; // Create a buffer of the specified size 
        System.out.println("Buffer contents:"); // Print a label before the buffer contents
        for (int i=0; i<b.length; i++){ // Iterate over each element in the buffer 
            System.out.printf("%d ", b[i]); // Print the value of each element in the buffer, followed by a space
        }
    }
}