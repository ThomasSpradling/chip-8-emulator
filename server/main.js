const express = require('express');
const path = require('path');

const app = express();
const port = 3000;

app.use(express.static(path.join(__dirname, '../web')));

// app.get('/file/:name', async (req, res) => {
//   const { filename } = req.params;
//   const filePath = `../roms/example${path.join(__dirname, filename);

//   const stat = await fs.stat(filePath);
//   res.writeHead(200, {
//     'Content-Type': 'text/plain',
//     'Content-Length': stat.size
//   });

//   const readStream = fs.createReadStream(filePath);
//   readStream.pipe(res);
// });

app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});
