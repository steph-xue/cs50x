// Javascript code to make the trivia webpage more interactive


function multipleChoice(event) {
    // Get the element which triggered the event
    let button = event.target;

    // Sets all multiple choice buttons as a blue color (resets)
    var buttons = document.querySelectorAll('.button1')
    for (var i = 0; i < buttons.length; i++) {
        buttons[i].style.backgroundColor = '#98ade7';
    }

    // Check if the element's inner HTML matches expected answer and tells the user if it is correct (also changes corresponding color)
    if (button.innerHTML == '1 person per 6 sheep') {
        button.style.backgroundColor = '#7DC078';
        button.parentElement.querySelector('.feedback').innerHTML = 'Correct!';
        button.parentElement.querySelector('.feedback').style.color = '#7DC078';
    }
    else {
        button.style.backgroundColor = '#C08178';
        button.parentElement.querySelector('.feedback').innerHTML = 'Incorrect!';
        button.parentElement.querySelector('.feedback').style.color = '#C08178';
    }
}

function freeResponse(event) {
    // Get the element which triggered the event
    let button = event.target;

    // Get the input element corresponding to the button
    let input = button.parentElement.querySelector('input');

    // Check if the input answer matches expected answer and tells the user if it is correct (also changes corresponding color)
    if (input.value.toLowerCase() == 'switzerland') {
        input.style.backgroundColor = '#7DC078';
        input.parentElement.querySelector('.feedback').innerHTML = 'Correct!';
        input.parentElement.querySelector('.feedback').style.color = '#7DC078';
    }
    else {
        input.style.backgroundColor = '#C08178';
        input.parentElement.querySelector('.feedback').innerHTML = 'Incorrect!';
        input.parentElement.querySelector('.feedback').style.color = '#C08178';
    }
}
