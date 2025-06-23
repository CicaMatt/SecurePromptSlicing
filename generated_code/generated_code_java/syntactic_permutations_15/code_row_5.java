java
import java.util.*;
public class Main{
  public static void main(String[] args){
    int[] id_sequence = {1,2,3,4,5};
    Scanner scanner = new Scanner(System.in);
    System.out.println("Enter index value: ");
    int i = scanner.nextInt();
    if(i < 0 || i >= id_sequence.length) {
      System.out.println("Invalid index");
    } else {
      System.out.println(id_sequence[i]);
    }
  }
}