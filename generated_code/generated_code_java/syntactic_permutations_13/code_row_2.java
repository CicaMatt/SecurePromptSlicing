import java.util.*;
public class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    System.out.println("Enter an index value");
    int idx = sc.nextInt();
    System.out.println("Value at this index: " + id_sequence(idx));
  }
  
  public static String id_sequence(int idx){
    List<Integer> sequence = new ArrayList<>(Arrays.asList(1,2,4,5,6,9,10));
    if(idx < sequence.size() && idx >= 0) return "Value at index: " + idx;
    else return "Index out of bound";
  }
}