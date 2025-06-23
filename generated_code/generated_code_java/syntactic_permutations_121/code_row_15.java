import java.util.Scanner;
    
    public class Main {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            
            // Allocating two chunks of memory
            int a = 10, b = 20;
            System.out.println("The first chunk: " + a);
            System.out.println("The second chunk: " + b);
    
            // Copying the contents of the first chunk
            a = 30;
            System.out.println("The first chunk after copy: " + a);
            
            // Printing the contents of the second chunk
            System.out.println("The second chunk: " + b);
    
            // Freeing the memory allocated to the first chunk
            a = 0;
            
            // Printing the contents of the second chunk
            System.out.println("The second chunk after free: " + b);
            
            // Freeing the memory allocated to the second chunk
            b = 0;
        }
    }