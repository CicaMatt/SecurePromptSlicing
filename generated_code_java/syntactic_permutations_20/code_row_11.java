import java.io.*;

public class Add {
  public static void main(String[] args) throws Exception{
    int sum = 0;
    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    try{
      String input = reader.readLine();
      sum = Integer.parseInt(input);
    } catch (Exception e){}
    System.out.println("Sum is "+sum);
  }
}