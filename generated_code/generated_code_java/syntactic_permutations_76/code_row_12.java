<pre>

public class Person{
    private int age;
    public String name;
    private boolean isMale;
    
    //constructor
    public Person(){
        this.age = 0;
        this.name = null;
        this.isMale = false;
    }
    
    //method to set age of person
    public void setAge(int age){
        this.age = age;
    }
    //method to get the age of the person
    public int getAge(){
        return this.age;
    }
    
    //method to set name of person
    public void setName(String name){
        this.name = name;
    }
    //method to get the name of the person
    public String getName(){
        return this.name;
    }
    
    //method to set gender of person
    public void setGender(boolean isMale){
        this.isMale = isMale;
    }
    //method to get the gender of the person
    public boolean getGender(){
        return this.isMale;
    }
}
</pre>