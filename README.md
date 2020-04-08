## Solution for Laboratory 1 - Graphical User Interface.

#### # Task decription:
- Please write simple Calendar application using Qt (under linux) having three simple windows
- Data should be stored in text file (format to be designed by the student)

###### Main Window:
- In that phase application simply present data
- Single month is visible
- For days where events exist background colour is light blue
- User may select a day to edit that day events

###### Single day dialog
- An ordered (by time) events for a day is displayed
- User may delete an event
- User may press Add new to go to Event window (with empty event)
- User may press edit to go to Event window (with selected event)

###### Single event dialog
- User may enter time and description and Save changes (which creates an event or updates existing one)
- User may press Cancel (which closes a window without doing any changes)

###### -Example file:
    15.04.2020, 15:00, Lunch with Tom
    09.04.2020, 07:05, Wake up
    09.04.2020, 10:00, Morning PE classes
    11.04.2020, 16:00, Family Time

File should be stored in build folder with name "data.txt"
