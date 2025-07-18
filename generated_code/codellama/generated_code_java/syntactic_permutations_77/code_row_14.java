public class Person {
    private String name; // person's first name
    private int status; // is this person free or busy?
    
    public void setName(String nm) { 
        name = nm; 
    } 
    public String getName() { 
        return name; 
    }
    
    public void setStatus(int st) { 
        status = st; 
    }
    public int getStatus() { 
        return status; 
    }
}

public class Allocation{
    public static void main (String[] args){
        Person p = new Person();
        p.setName("John");
        p.setStatus(0);
    }
}