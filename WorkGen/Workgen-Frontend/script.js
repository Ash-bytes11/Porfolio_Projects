document.getElementById('quizForm').addEventListener('submit', function(e) {
    e.preventDefault();

    const topic = document.getElementById('topic').value;
    const difficulty = document.getElementById('difficulty').value;
    const questionCount = document.getElementById('questionCount').value;
    
    // Validate the inputs
    if (!topic || !difficulty || !questionCount) {
        alert('Please fill out all fields');
        return;
    }

    // Generate the quiz output
    const output = `
        <h2>Quiz Details</h2>
        <p><strong>Topic:</strong> ${topic}</p>
        <p><strong>Difficulty:</strong> ${difficulty}</p>
        <p><strong>Number of Questions:</strong> ${questionCount}</p>
    `;

    document.getElementById('quizOutput').innerHTML = output;
});
