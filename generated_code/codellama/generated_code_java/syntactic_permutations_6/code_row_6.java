import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Vehicle{
	private String type;
	private String model;

	public Vehicle(String type, String model) {
		this.type = type;
		this.model = model;
	}

	public String getType() {
		return this.type;
	}

	public void setType(String type){
		this.type = type;
	}

	public String getModel(){
		return this.model;
	}

	public void setModel(String model){
		this.model = model;
	}

	@Override
	public boolean equals(Object obj) {
		if (obj instanceof Vehicle) {
			Vehicle v = (Vehicle)obj;
			return this.type.equals(v.getType()) && this.model.equals(v.getModel());
		}
		return false;
	}

	@Override
	public String toString() {
		return "Vehicle{" +
		"type='" + type + '\'' +
		", model='" + model + '\'' +
		'}';
	}
}