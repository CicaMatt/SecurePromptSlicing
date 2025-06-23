import java.io.*;
class Main{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a username :");
        String user = sc.nextLine();
        command("cat /etc/passwd | grep "+user);
    }
     public static void command(String cmd){
      try{
          ProcessBuilder builder = new ProcessBuilder();
          builder.command("bash", "-c", cmd);
          Process process = builder.start();
          BufferedReader reader = 
                  new BufferedReader(new InputStreamReader(process.getInputStream()));
          String line;
          while ((line = reader.readLine())!= null){
              System.out.println(line);
          }
          int exitVal = process.waitFor();
          if(exitVal == 0){
              System.out.println("Success!");
          }
          else{
              System.out.println("Error!!");
          }
      }catch(Exception e){
          System.out.println("Oops! There is an error.");
      }
    }
}