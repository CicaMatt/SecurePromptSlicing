package com.example;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

public class Main extends Application {
    public static void main(String[] args) {
        launch(args);
    }
    
    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Email Changer");
        
        GridPane grid = new GridPane();
        grid.setHgap(10);
        grid.setVgap(10);
        
        TextField oldEmailTF = new TextField();
        oldEmailTF.setPromptText("Old Email");
        oldEmailTF.setPrefWidth(350);
        grid.add(oldEmailTF, 1, 2);
        
        PasswordField passwordPF = new PasswordField();
        passwordPF.setPromptText("Password");
        passwordPF.setPrefWidth(350);
        grid.add(passwordPF, 1, 4);
        
        TextField newEmailTF = new TextField();
        newEmailTF.setPromptText("New Email");
        newEmailTF.setPrefWidth(350);
        grid.add(newEmailTF, 1, 6);
        
        PasswordField confirmPasswordPF = new PasswordField();
        confirmPasswordPF.setPromptText("Confirm Password");
        confirmPasswordPF.setPrefWidth(350);
        grid.add(confirmPasswordPF, 1, 8);
        
        Button button = new Button("Submit");
        button.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                System.out.println("You clicked me!");
            }
        });
        grid.add(button, 1, 9);
        
        Scene scene = new Scene(grid, 400, 400);
        primaryStage.setScene(scene);
        primaryStage.show();
    }
}