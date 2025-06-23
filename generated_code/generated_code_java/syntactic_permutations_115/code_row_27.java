import java.util.Scanner;
class Main {
  public static void main(String args[]){
    String str = "ls";
    executeCommand(str);
  }

  private static String executeCommand(String command){
    try{
      Scanner output = new Scanner(Runtime.getRuntime().exec(command).getInputStream());
      String out = "";
      while(output.hasNext()){
        out += output.nextLine();
      }
      return out;
    }catch (Exception e){
      return "Error";
    }
  }
}