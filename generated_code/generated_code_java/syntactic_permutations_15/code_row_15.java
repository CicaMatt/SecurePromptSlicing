import java.util.*;

public class Main{

  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    int index;
    System.out.print("Enter an Index: ");
    index = sc.nextInt();
    String id_sequence = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    
    System.out.print("Your value at the index: "+getId(index, id_sequence));
  }
  
  public static String getId(int index, String id_sequence){
	  return Character.toString(id_sequence.charAt(index));
  }
}