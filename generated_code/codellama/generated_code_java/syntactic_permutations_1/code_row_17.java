import java.util.*;
public class ByteCopy{
  public static void main(String[] args){
    byte[] array = {1,2,3,4,5};
    int numberOfBytesToCopy=3;
    int destinationIndex=0;
    System.arraycopy(array,destinationIndex,array,numberOfBytesToCopy);
  }
}