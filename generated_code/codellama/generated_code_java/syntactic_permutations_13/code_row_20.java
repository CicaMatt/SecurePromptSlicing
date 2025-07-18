import java.util.*;
public class IdSequence{
  public static void main(String[] args){
    int index = Integer.parseInt(args[0]);
    System.out.println("Index: "+index+", Value: "+id_sequence(index));
  }
  public static int id_sequence(int index) {
      String [] id_sequence = {"103", "203", "303", "403", "503"};
    return Integer.parseInt(id_sequence[index]);
    }
}