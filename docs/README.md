# Contributing to MMX Documentation

If you would like to contribute to MMX Documentation, you can do so by following these steps:
1. Fork the repository
2. Clone *your fork* repository and cd into it
3. Create a new branch
4. Make your changes:
    - First cd into the `docs` directory
    - Run `npm install` to install dependencies (requires Node.js/npm)
    - Run `npm run dev` to start the local server
    - Make your changes in your favorite code editor
5. Commit your changes
6. Push to your fork
7. Create a pull request


Clicking the `Edit page` button at the bottom of docs pages will take you to the source file for that page and prompt you to create or add to your fork of mmx-node to submit a pull request. If you want to add a new page, you can do so by creating a new `.md` or `.mdx` file in the appropriate subdirectory for the category desired. View existing files for formatting examples. Creating a new category for the sidebar can be done by creating a new directory in `src/content/docs/` and then adding that directory to the `sidebar` array in `astro.config.mjs`.


See below for the basic structure of the docs, npm commands, and links to the full starlight and astro documentation.

## 🚀 Project Structure

Inside of your Astro + Starlight project, you'll see the following folders and files:

```
.
├── public/
├── src/
│   ├── assets/
│   ├── content/
│   │   ├── docs/
│   └── content.config.ts
├── astro.config.mjs
├── package.json
└── tsconfig.json
```

Starlight looks for `.md` or `.mdx` files in the `src/content/docs/` directory. Each file is exposed as a route based on its file name.

Images can be added to `src/assets/` and embedded in Markdown with a relative link.

Static assets, like favicons, can be placed in the `public/` directory.

## 🧞 Commands

All commands are run from the root of the project, from a terminal:

| Command                   | Action                                           |
| :------------------------ | :----------------------------------------------- |
| `npm install`             | Installs dependencies                            |
| `npm run dev`             | Starts local dev server at `localhost:4321`      |
| `npm run build`           | Build your production site to `./dist/`          |
| `npm run preview`         | Preview your build locally, before deploying     |
| `npm run astro ...`       | Run CLI commands like `astro add`, `astro check` |
| `npm run astro -- --help` | Get help using the Astro CLI                     |

## 👀 Want to learn more?

Check out [Starlight’s docs](https://starlight.astro.build/), read [the Astro documentation](https://docs.astro.build), or jump into the [Astro Discord server](https://astro.build/chat).
