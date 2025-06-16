import java.io.*; 
     class Solution { 
       public static void main(String[] args) throws IOException { 
          String str = "ls"; 
         executeCommand(str); 
      } 
      //Function to execute command 
      private static void executeCommand(String str) throws IOException{ 
        Process p = Runtime.getRuntime().exec(str); 
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream())); 
        String line; 
         while((line=reader.readLine())!= null){ 
            System.out.println(line); 
          } 
       } 
    }