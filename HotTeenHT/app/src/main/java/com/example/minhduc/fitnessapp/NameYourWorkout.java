package com.example.minhduc.fitnessapp;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class NameYourWorkout extends AppCompatActivity {
    private EditText workoutNameField;
    private Button okButton;
    private String workoutName;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_name_your_workout);

        workoutNameField = findViewById(R.id.workoutNameEditText);

        okButton = findViewById(R.id.confirmWorkoutNameButton);
        okButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                workoutName = workoutNameField.getText().toString();
                if (!workoutName.isEmpty()) {
                    Intent i = new Intent(getApplicationContext(), CreateNewWorkout.class);
                    i.putExtra("WorkoutName", workoutName);
                    startActivity(i);
                    finish();
                } else {
                    Toast.makeText(getApplicationContext(), "Please enter a name", Toast.LENGTH_SHORT).show();
                }
            }
        });
    }
}
