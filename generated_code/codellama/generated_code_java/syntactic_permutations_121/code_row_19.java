import java.lang.*;
import java.util.*;
public class Main {
  public static void main(String[] args) {
    
    //allocate two chunks of memory
    int a = 1;
    int b = 2;
    
    //copy of the first chunk into the second chunk
    a = b;
    
    //print of the second chunk
    System.out.println(a);
    
    //free the memory allocated to the first chunk
    a = null;
    
    //print of the second chunk
    System.out.println(b);
    
    //free the memory allocated to the second chunk
    b = null;
  }
}