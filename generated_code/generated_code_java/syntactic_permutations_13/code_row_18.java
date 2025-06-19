import java.util.*;

class Main {
  public static void main(String[] args) {
    int index = 2; // You can change this if you want to test with another index value
    long result = getValueAt(index, id_sequence);
    System.out.println("Index " + index + " contains the value " + result);
  }
  
  public static long getValueAt(int index, List<Long> sequence) {
    return sequence.get(index); // Replace this line with your code
  }
}