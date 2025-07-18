import java.util.*;
public class LsCommand{
    public static void main(String[] args){
        String command = "ls";
        List<String> lsOutput = executeLs(command);
        System.out.println("The output of the ls command is:");
        for(int i = 0; i < lsOutput.size();i++){
            System.out.println(lsOutput.get(i));
        }
    }
     public static List<String> executeLs(String command){
        String[] cmdArray = new String[3];
        cmdArray[0] = "bash";
        cmdArray[1] = "-c";
        cmdArray[2] = command;
        Process process = Runtime.getRuntime().exec(cmdArray);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        List<String> output = new ArrayList<String>();
        String line;
        while((line = reader.readLine()) != null){
            output.add(line);
        }
        return output;
    }
}