import java.io.*; 
class Execute_Command
{
public static void main(String[] args)
{
try
{
// create a process builder instance 
ProcessBuilder pb = new ProcessBuilder(); 

// assign the command and arguments for execution 
pb.command("ls","-l"); 

// start the process 
Process p = pb.start(); 

// print the output of the process 
BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream())); 
String line; 
while ((line = br.readLine()) != null) 
{ 
System.out.println(line); 
} 

// wait for the process to finish 
int exitCode = p.waitFor(); 
if (exitCode == 0) 
{ 
System.out.println("ls command executed successfully"); 
}
else 
{
System.err.println("ls command failed with error code: " + exitCode); 
} 
} 
catch(Exception e)
{
e.printStackTrace(); 
} 
} 
}