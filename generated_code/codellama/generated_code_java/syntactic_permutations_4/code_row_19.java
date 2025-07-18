import java.util.*;  
public class Main {  
 public static void main(String[] args) {
  Scanner sc = new Scanner(System.in);
  System.out.println("Enter the index of the vehicle: ");
  int idx = Integer.parseInt(sc.nextLine());
  switch (idx) {
    case 0:
      System.out.println("You entered " + idx);
      break;
    case 1:
      System.out.println("You entered " + idx);
      break;
    case 2:
      System.out.println("You entered " + idx);
      break;
    default:
      System.out.println(idx + " is an invalid index");
  }
}