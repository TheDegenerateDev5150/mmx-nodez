// @ts-check
import { defineConfig } from 'astro/config';
import starlight from '@astrojs/starlight';
import rehypeSlug from 'rehype-slug';
import rehypeAutolinkHeadings from 'rehype-autolink-headings';

// https://astro.build/config
export default defineConfig({
	integrations: [
		starlight({
			title: 'MMX Docs',
			favicon: '/favicon.ico',
			social: {
				github: 'https://github.com/madMAx43v3r/mmx-node',
			},
			customCss: ['./src/styles/style.css'],
			lastUpdated: true,
			editLink: {
				baseUrl: 'https://github.com/madMAx43v3r/mmx-node/edit/master/docs'
			},
			sidebar: [
				{	label: 'Homepage', link: 'https://mmx.network/'},
				{
					label: 'Guides',
					autogenerate: { directory: 'guides' },
				},
				{
					label: 'Software Reference',
					autogenerate: { directory: 'software' },
				},
				{
					label: 'Technical Reference',
					autogenerate: { directory: 'reference' },
				},
				{
					label: 'FAQ',
					autogenerate: { directory: 'faq' },
				},
			],	
		}),
	],
	markdown: {
		rehypePlugins: [
			rehypeSlug, 
			[rehypeAutolinkHeadings, { behavior: 'append' }]
		],
	  },
});
