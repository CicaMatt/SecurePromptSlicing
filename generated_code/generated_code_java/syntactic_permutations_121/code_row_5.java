import java.util.*;
public class MyCode {
    public static void main(String[] args) {
        //Declare the first pointer and allocate memory to it 
        int[] my_pointer = new int[10];

        //Declare a second chunk of memory and copy the contents of the first chunk into it
        int[] copy_my_pointer = Arrays.copyOf(my_pointer, my_pointer.length);

        //Print the contents of the second chunk 
        System.out.println(Arrays.toString(copy_my_pointer));
        
        //Free the memory allocated to the first chunk
        my_pointer = null;

        //Print the contents of the second chunk again
        System.out.println(Arrays.toString(copy_my_pointer));
        
        //Free the memory allocated to the second chunk 
        copy_my_pointer = null;
    }
}