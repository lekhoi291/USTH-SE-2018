package com.example.minhduc.fitnessapp;

import android.support.test.espresso.assertion.ViewAssertions;
import android.support.test.rule.ActivityTestRule;
import android.support.test.runner.AndroidJUnit4;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

import static android.support.test.espresso.Espresso.onView;
import static android.support.test.espresso.action.ViewActions.click;
import static android.support.test.espresso.action.ViewActions.longClick;
import static android.support.test.espresso.action.ViewActions.replaceText;
import static android.support.test.espresso.matcher.RootMatchers.withDecorView;
import static android.support.test.espresso.matcher.ViewMatchers.isDisplayed;
import static android.support.test.espresso.matcher.ViewMatchers.withClassName;
import static android.support.test.espresso.matcher.ViewMatchers.withId;
import static android.support.test.espresso.matcher.ViewMatchers.withText;

import static org.hamcrest.core.AllOf.allOf;
import static org.hamcrest.core.StringEndsWith.endsWith;
import static android.support.test.espresso.assertion.ViewAssertions.matches;
import static org.hamcrest.Matchers.is;
import static org.hamcrest.Matchers.not;

@RunWith(AndroidJUnit4.class)
public class MainActivityTest {
    @Rule
    public ActivityTestRule<MainActivity> activityTestRule =
            new ActivityTestRule<>(MainActivity.class);

    @Test
    public void ShouldBeAbleToLaunchMainScreen(){
        onView(withText("Ready to start?")).check(ViewAssertions.matches(isDisplayed()));
    }

    @Test
    public void testListViewBehavior() {
        String name1 = "Arms";
        String name2 = "Legs";
        // Click the lets go button
        onView(withId(R.id.customWorkoutButton)).perform(click());
        // Click the add button
        onView(withId(R.id.addWorkoutButton)).perform(click());
        // Type the name
        onView(allOf(withClassName(endsWith("EditText")), withText(is("")))).perform(replaceText(name1));
        // Save the exercise
        onView(withId(R.id.confirmWorkoutNameButton)).perform((click()));
        // Click finish
        onView(withId(R.id.buttonFinish)).perform(click());
        // Check if its appear on menu
        onView(withText(name1)).check(ViewAssertions.matches(isDisplayed()));
        // Hold the name1 workout line
        onView(withText(name1)).perform(longClick());
        // Click Rename
        onView(withText("Rename")).perform(click());
        // Rename the workout
        onView(allOf(withClassName(endsWith("EditText")), withText(is("")))).perform(replaceText(name2));
        // Click OK
        onView(withText("OK")).perform(click());
        // Check if its rename it or not
        onView(withText(name2)).check(ViewAssertions.matches(isDisplayed()));
        // Hold the name2 workout line
        onView(withText(name2)).perform(longClick());
        // Click Delete
        onView(withText("Delete")).perform(click());
        // Click Ok
        onView(withText("OK")).perform(click());
        // Check if its not appear on menu
        onView(withText(name2)).check(ViewAssertions.doesNotExist());
    }
    @Test
    public void testNameConstraint(){
        // Click the lets go button
        onView(withId(R.id.customWorkoutButton)).perform(click());
        // Click the add button
        onView(withId(R.id.addWorkoutButton)).perform(click());
        // Save the exercise
        onView(withId(R.id.confirmWorkoutNameButton)).perform((click()));
        MainActivity activity = activityTestRule.getActivity();
        onView(withText("Please enter a name")).
                inRoot(withDecorView(not(is(activity.getWindow().getDecorView())))).
                check(matches(isDisplayed()));
    }
}
