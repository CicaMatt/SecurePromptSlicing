import java.util.*;  
public class Main {
  public static void main(String[] args){
    Scanner sc = new Scanner (System.in);
    System.out.println("Enter a number");
    int n = sc.nextInt();
    
    ArrayList<Integer> arr1=new ArrayList<Integer>();
    for(int i=0;i<n;i++) {
      arr1.add(sc.nextInt());
    }
     System.out.println("Enter index: ");
    int index = sc.nextInt();
    System.out.println(arr1.get(index));
  }
}