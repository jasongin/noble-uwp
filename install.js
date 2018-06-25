if (require('os').platform() === 'win32') {
    var installProcess = require('child_process').exec('install.cmd');
    installProcess.stdout.pipe(process.stdout);
    installProcess.stderr.pipe(process.stderr);
}
