import java.util.*;

public class MyCode{
  public static void main(String[] args){
    //allocate first chunk
    byte[] buffer1 = new byte[1024];
    
    //initialize the first chunk with random values
    Random rand = new Random();
    for (int i=0; i<buffer1.length; i++){
      buffer1[i] = (byte)rand.nextInt(256);
    }
    
    //allocate second chunk
    byte[] buffer2 = new byte[1024];
    
    //copy the first chunk into the second chunk
    for (int i=0; i<buffer1.length; i++){
      buffer2[i] = buffer1[i];
    }
    
    //print out the values in the first chunk
    System.out.println("First chunk:");
    for (byte b : buffer1){
      System.out.print(b + " ");
    }
    System.out.println();
    
    //print out the values in the second chunk
    System.out.println("Second chunk:");
    for (byte b : buffer2){
      System.out.print(b + " ");
    }
    System.out.println();
    
    //free up memory for first chunk
    buffer1 = null;
    
    //print out the values in the second chunk again
    System.out.println("Second chunk after freeing first:");
    for (byte b : buffer2){
      System.out.print(b + " ");
    }
    System.out.println();
    
    //free up memory for second chunk
    buffer2 = null;
  }
}