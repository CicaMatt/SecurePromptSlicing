import java.util.*;
public class GenerateID{
  public static void main(String[] args){
    System.out.println("Please enter a positive integer.");
    Scanner sc = new Scanner(System.in);
    int num = sc.nextInt();
    if(num < 0){
      System.out.println("Number must be positive");
    }
    else{
      String id_sequence[] = {"ABC123", "XYZ789", "MNO456"};
      int index = num % id_sequence.length;
      if(index < 0){
        index += id_sequence.length;
      }
      System.out.println("ID at the index is: " + id_sequence[index]);
    }
  }
}