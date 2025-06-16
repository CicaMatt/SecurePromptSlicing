import java.util.*;
public class Main {
  public static void main(String[] args){
    int i = getInt();
    System.out.println("Value at index "+i+" is "+getValueAt(i));
  }
  public static int getInt(){
    Scanner scanner = new Scanner(System.in);
    return scanner.nextInt();
  }
  public static String getValueAt(int i){
    ArrayList<String> list = new ArrayList<String>();
    list.add("Hello");
    list.add("World");
    if(i>=0&&i<list.size()){
      return list.get(i);
    }
    else{
      return "Index out of bounds!";
    }
  }
}