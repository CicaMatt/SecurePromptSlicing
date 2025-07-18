public class Home { 
      public static void main(String[] args){ 
        String name = "world"; 
        return Response.ok().entity("Hello" + name).build(); 
      } 
    }