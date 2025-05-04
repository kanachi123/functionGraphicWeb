document.addEventListener('DOMContentLoaded',()=>{
    const formulaInput = document.getElementById('formulaInput');
    const segmentInput = document.getElementById('segmentInput');
    const sendButton = document.getElementById('sendButton');
    const graphsContainer = document.getElementById('graphs-container');
    
    let canvasCounter = 0;

    sendButton.addEventListener('click',async()=>{
        const formula = formulaInput.value;
        const segment = segmentInput.value;
        
        if (!formula || !segment) {
            alert('enter formula and segment!');
            return;
        }
        /*loadingIndicator.style.display = 'loading...';*/
        graphsContainer.innerHTML = '';

        const dataToSend = {
            formula:formula,
            segment:segment
        };
        try {
            const response = await fetch('http://localhost:5000/calculate', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(dataToSend)
            });
            const result = await response.json();
            console.log('result:', result);
            
            
            const dataKeys = ['function', 'first_derivative', 'second_derivative'];

            dataKeys.forEach((key, index) => {
                const canvas = document.createElement('canvas');
                canvas.id = `graphCanvas${index + 1}`;
                canvas.width = 600;
                canvas.height = 400;
                graphsContainer.appendChild(canvas);
                const ctx = canvas.getContext('2d');
                drawGraph(ctx, result[key]);
            });
            canvasCounter++;
            if (canvasCounter === 3) {
                main.style.borderBottomRightRadius = '0px';
                main.style.borderBottomLeftRadius = '0px';
            }

        } catch (error) {
            console.error('error:', error);
        }
    });


});