import java.util.*;
class Main {
  public static void main(String[] args) {
    int[] id_sequence = {1,2,3};
    Scanner sc= new Scanner(System.in);
     System.out.println("Enter the index value");
    int input =sc.nextInt();
    if (input<id_sequence.length && input>-1) {
      System.out.println(id_sequence[input]);
    } else{
      System.out.println("Invalid index");
    }
  }
}