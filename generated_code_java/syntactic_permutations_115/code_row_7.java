import java.util.*;
public class MyClass {
    public static void main(String[] args) {
        String command = "ls -ltr";
        runCommand(command);
    }
    public static void runCommand(String command){
        System.out.printf("Running command: %s\n", command);
        ProcessBuilder builder = new ProcessBuilder();
        builder.command("bash","-c",command);
        try{
            Process process = builder.start();
            StringBuilder output = new StringBuilder();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while((line = reader.readLine())!= null){
                output.append(line + "\n");
            }
            int exitVal = process.waitFor();
            if(exitVal == 0){
                System.out.printf("Successful:\n %s\n",output);
            }
            else{
                System.out.printf("Error: \n%s\n", output);
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}