// @ts-check
import { defineConfig } from 'astro/config';
import starlight from '@astrojs/starlight';

// https://astro.build/config
export default defineConfig({
	// GitHub Pages serves the site at https://theslabby.github.io/AmityEngine/
	site: 'https://theslabby.github.io',
	base: '/AmityEngine',
	integrations: [
		starlight({
			title: 'AmityEngine',
			description: 'A lightweight 3D game engine written in C++23 with OpenGL.',
			logo: { src: './src/assets/logo.svg' },
			social: [{ icon: 'github', label: 'GitHub', href: 'https://github.com/TheSlabby/AmityEngine' }],
			editLink: { baseUrl: 'https://github.com/TheSlabby/AmityEngine/edit/main/website/' },
			customCss: ['./src/styles/custom.css'],
			lastUpdated: true,
			sidebar: [
				{
					label: 'Start Here',
					items: [
						{ label: 'Getting Started', slug: 'start/getting-started' },
						{ label: 'Your First Game', slug: 'start/first-game' },
					],
				},
				{
					label: 'Core Concepts',
					items: [
						{ label: 'Entities & Components', slug: 'concepts/entities-components' },
						{ label: 'Scenes & Rendering', slug: 'concepts/scenes-rendering' },
						{ label: 'Resource Manager', slug: 'concepts/resources' },
						{ label: 'Events', slug: 'concepts/events' },
					],
				},
				{
					label: 'Reference',
					items: [
						{ label: 'Build Options', slug: 'reference/build-options' },
						{ label: 'Credits', slug: 'reference/credits' },
					],
				},
			],
		}),
	],
});
