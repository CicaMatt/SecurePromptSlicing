import java.util.*;
	public class Person{
		private int id;
		private String name;
		public Person(int id,String name){
			this.id=id;
			this.name=name;
		}
		public void setID(int i){
			this.id=i;
		}
		public int getID(){
			return id;
		}
		public void setName(String n){
			this.name=n;
		}
		public String getName(){
			return name;
		}
	}
	public class allocator{
		private static int memorySize;
		static void allocates(int sizeOfPerson){
			memorySize=sizeOfPerson;
			Person p=new Person(0,null);
			p.setID(0);
		}
		public static void main(String[] args) {
			allocates(sizeof(person));
		}
	}