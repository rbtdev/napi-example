let addon = require('../index.js');
let os = require('os');
let cpuCount = os.cpus().length;

console.log(JSON.stringify(addon, null, 2))
let tasks = [];
for (let i = 1; i <= cpuCount; i++) {
    tasks.push(addon.run(addon.BIG_NUMBER));
    console.log(`Task ${i} of ${cpuCount} started on separate thread`);
}
Promise.all(tasks).then(results => {
    clearInterval(timer);
    console.log(results);
});

let timer = setInterval(() => {
    console.log(new Date());
}, 1000);

console.log('Compute tasks running in sepatate threads. Timer running');
