import java.util.*;
public class HelloWorld{
  public static void main(String []args){
    //Allocate two chunks of memory
    int[] chunk1 = new int[3];
    int[] chunk2 = new int[3];
    
    //Copy contents of first chunk into second chunk
    System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);
    
    //Print the contents of the second chunk
    for (int i = 0; i < chunk2.length; i++) {
      System.out.println("The contents of the second chunk are: " + chunk2[i]);
    }
    
    //Free memory allocated to first chunk
    chunk1 = null;
    
    //Print the contents of the second chunk again
    for (int i = 0; i < chunk2.length; i++) {
      System.out.println("The contents of the second chunk are: " + chunk2[i]);
    }
    
    //Free memory allocated to second chunk
    chunk1 = null;
  }
}