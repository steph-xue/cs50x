// Javascript code to make the trivia webpage more interactive

// Wait for DOM content to load
document.addEventListener('DOMContentLoaded', function() {

    // Get all elements (buttons) with class "correct"
    let corrects = document.querySelectorAll('.correct');

    // Add event listeners to each correct button for the multiple choice question (check if any are clicked)
    for (let i = 0; i < corrects.length; i++) {
        corrects[i].addEventListener('click', function() {

            // Turns all other buttons back to blue when a button is clicked
            var buttons = document.querySelectorAll('.button1')
            for (let j = 0; j < buttons.length; j++) {
                buttons[j].style.backgroundColor = '#98ade7';
            }

            // Set background color of the correct button clicked to green
            corrects[i].style.backgroundColor = '#7DC078';

            // Go to parent element of correct button and find the first element with class "feedback" which has that parent to change to a green 'Correct'
            corrects[i].parentElement.querySelector('.feedback').innerHTML = 'Correct';
            corrects[i].parentElement.querySelector('.feedback').style.color = '#7DC078';
        });
    }

    // Get all elements (buttons) with class "incorrect"
    let incorrects = document.querySelectorAll('.incorrect');

    // Add event listeners to each incorrect button for the multiple choice question (check if any are clicked)
    for (let i = 0; i < incorrects.length; i++) {
        incorrects[i].addEventListener('click', function() {

            // Turns all other buttons back to blue when a button is clicked
            var buttons = document.querySelectorAll('.button1')
            for (let j = 0; j < buttons.length; j++) {
                buttons[j].style.backgroundColor = '#98ade7';
            }

            /// Set background color of the correct button clicked to red
            incorrects[i].style.backgroundColor = '#C08178';

            // Go to parent element of correct button and find the first element with class "feedback" which has that parent to change to a red 'Incorrect'
            incorrects[i].parentElement.querySelector('.feedback').innerHTML = 'Incorrect';
            incorrects[i].parentElement.querySelector('.feedback').style.color = '#C08178';
        });
    }

    // Check free response submission (checks if submit button is clicked)
    document.querySelector('.check').addEventListener('click', function() {
        let input = document.querySelector('input')

        // Checks if the input is the correct answer (Switzerland) to turn it green
        if (input.value.toLowerCase() == 'switzerland') {
            input.style.backgroundColor = '#7DC078';
            input.parentElement.querySelector('.feedback').innerHTML = 'Correct';
            input.parentElement.querySelector('.feedback').style.color = '#7DC078';
        }
        // If the input is incorrect, it turns it red
        else {
            input.style.backgroundColor = '#C08178';
            input.parentElement.querySelector('.feedback').innerHTML = 'Incorrect';
            input.parentElement.querySelector('.feedback').style.color = '#C08178';
        }
    });
});

