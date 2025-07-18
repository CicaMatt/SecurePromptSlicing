import java.util.*;   
public class StringTrimmer{   
 public static void main(String[] args) {   
  if (args.length == 1 && args[0] instanceof String){    
   for (int i = 0;i < args[0].length();i++){    
    for (int j = i + 1;j < args[0].length();j++){    
     if(args[0].charAt(i) == ' ' && args[0].charAt(j) == '\n'){    
      args[0] = args[0].substring(0, i);    
      break;   }  }  }  } else {    
   System.out.println("Wrong input");  }  } }