import java.util.*;
public class Main{
  public static void main(String[] args){
    int[] id_sequence = {1,2,3,4,5};
    Scanner sc = new Scanner(System.in);
    System.out.println("Enter an index value: ");
    int i=sc.nextInt();
    System.out.print("Value at the index is "+id_sequence[i]);
  }
}